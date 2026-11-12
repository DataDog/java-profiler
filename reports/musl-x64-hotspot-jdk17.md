---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:40:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1794504883 79
1794504888 79
1794504893 81
1794504898 81
1794504903 81
1794504908 81
1794504913 81
1794504918 81
1794504923 81
1794504928 83
1794504934 83
1794504939 83
1794504944 83
1794504949 83
1794504954 83
1794504959 83
1794504964 83
1794504969 83
1794504974 83
1794504979 83
```
</details>

---

