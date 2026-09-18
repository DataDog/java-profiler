---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 48-70 cores)</summary>

```
1789716706 48
1789716711 48
1789716716 48
1789716721 48
1789716726 48
1789716731 49
1789716736 49
1789716741 49
1789716746 49
1789716751 49
1789716756 49
1789716761 49
1789716766 49
1789716771 49
1789716776 49
1789716781 70
1789716786 70
1789716791 48
1789716796 48
1789716801 48
```
</details>

---

