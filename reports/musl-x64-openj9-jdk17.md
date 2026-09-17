---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 10:30:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 69-71 cores)</summary>

```
1789655045 71
1789655050 71
1789655055 71
1789655060 71
1789655065 71
1789655070 71
1789655075 69
1789655080 69
1789655085 69
1789655090 69
1789655095 69
1789655100 71
1789655105 71
1789655110 71
1789655115 71
1789655120 71
1789655125 71
1789655130 71
1789655135 71
1789655140 71
```
</details>

---

