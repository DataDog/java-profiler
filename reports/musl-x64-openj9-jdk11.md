---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 64-85 cores)</summary>

```
1794495880 64
1794495885 66
1794495890 66
1794495895 66
1794495900 66
1794495905 66
1794495910 66
1794495915 66
1794495920 85
1794495925 85
1794495930 85
1794495935 85
1794495940 85
1794495945 85
1794495950 85
1794495955 85
1794495960 85
1794495965 85
1794495970 85
1794495975 85
```
</details>

---

