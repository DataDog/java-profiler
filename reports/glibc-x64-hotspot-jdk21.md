---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 14:35:35 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 10-11 cores)</summary>

```
1793125858 11
1793125863 11
1793125868 11
1793125873 11
1793125878 11
1793125883 11
1793125888 11
1793125893 11
1793125898 11
1793125903 11
1793125908 10
1793125913 10
1793125918 10
1793125923 10
1793125928 10
1793125933 10
1793125938 10
1793125943 10
1793125948 10
1793125953 10
```
</details>

---

