---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:49:33 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1793295786 76
1793295791 76
1793295796 76
1793295801 76
1793295806 76
1793295811 76
1793295816 78
1793295821 78
1793295826 78
1793295831 78
1793295836 78
1793295841 78
1793295846 78
1793295851 78
1793295856 78
1793295861 78
1793295866 78
1793295871 78
1793295876 81
1793295881 81
```
</details>

---

