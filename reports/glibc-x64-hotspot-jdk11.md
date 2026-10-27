---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:00:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 47-51 cores)</summary>

```
1793120153 48
1793120158 48
1793120163 48
1793120168 48
1793120173 48
1793120178 50
1793120183 50
1793120188 51
1793120193 51
1793120198 51
1793120203 51
1793120208 51
1793120213 49
1793120218 49
1793120223 47
1793120228 47
1793120233 47
1793120238 47
1793120243 47
1793120248 47
```
</details>

---

