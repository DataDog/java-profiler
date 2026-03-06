---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 05:53:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 12 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 21-26 cores)</summary>

```
1772794074 26
1772794079 26
1772794084 26
1772794089 26
1772794094 26
1772794099 26
1772794104 26
1772794109 22
1772794114 22
1772794119 21
1772794124 21
1772794129 21
1772794134 23
1772794139 23
1772794144 23
1772794149 23
1772794154 23
1772794159 23
1772794164 23
1772794169 23
```
</details>

---

