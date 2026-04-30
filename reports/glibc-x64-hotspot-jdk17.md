---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 19:50:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 67-86 cores)</summary>

```
1777592888 67
1777592893 67
1777592898 67
1777592903 67
1777592908 67
1777592913 67
1777592918 72
1777592923 72
1777592928 72
1777592933 72
1777592938 72
1777592943 76
1777592948 76
1777592953 81
1777592958 81
1777592963 81
1777592968 81
1777592973 81
1777592978 81
1777592983 81
```
</details>

---

