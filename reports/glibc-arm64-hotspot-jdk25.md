---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-21 15:09:49 EDT

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
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 9 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 14 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787339128 43
1787339133 43
1787339138 43
1787339143 43
1787339148 43
1787339153 43
1787339158 43
1787339163 43
1787339168 43
1787339173 43
1787339178 48
1787339183 48
1787339188 48
1787339193 48
1787339198 48
1787339203 48
1787339208 48
1787339213 48
1787339218 48
1787339223 48
```
</details>

---

