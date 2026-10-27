---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:00:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793120174 43
1793120179 43
1793120184 43
1793120189 43
1793120194 43
1793120199 43
1793120204 43
1793120209 43
1793120214 43
1793120219 43
1793120224 43
1793120229 48
1793120234 48
1793120239 48
1793120244 48
1793120249 48
1793120254 48
1793120259 48
1793120264 48
1793120269 48
```
</details>

---

