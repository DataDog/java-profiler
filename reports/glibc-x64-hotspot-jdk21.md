---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 11:57:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1786463498 85
1786463503 85
1786463508 85
1786463513 85
1786463518 89
1786463524 89
1786463529 89
1786463534 89
1786463539 89
1786463544 89
1786463549 89
1786463554 89
1786463559 89
1786463564 89
1786463569 89
1786463574 89
1786463579 89
1786463584 87
1786463589 87
1786463594 87
```
</details>

---

