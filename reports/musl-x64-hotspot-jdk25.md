---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:42:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 73-90 cores)</summary>

```
1794324985 90
1794324990 90
1794324995 90
1794325000 90
1794325005 90
1794325010 90
1794325015 90
1794325020 90
1794325025 90
1794325030 90
1794325035 90
1794325040 90
1794325045 90
1794325051 90
1794325056 90
1794325061 90
1794325066 73
1794325071 73
1794325076 73
1794325081 73
```
</details>

---

