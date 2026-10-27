---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 12:59:27 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 12 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (3 unique values: 32-52 cores)</summary>

```
1793120133 41
1793120138 41
1793120143 41
1793120148 41
1793120153 41
1793120158 41
1793120163 41
1793120168 41
1793120173 41
1793120178 41
1793120183 41
1793120188 41
1793120193 41
1793120198 41
1793120203 41
1793120208 41
1793120213 41
1793120218 41
1793120223 41
1793120228 41
```
</details>

---

