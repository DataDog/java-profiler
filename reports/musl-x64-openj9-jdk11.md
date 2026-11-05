---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:11 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 60-61 cores)</summary>

```
1793890188 61
1793890193 61
1793890198 61
1793890203 61
1793890208 61
1793890213 61
1793890218 61
1793890223 61
1793890228 61
1793890233 61
1793890238 61
1793890243 61
1793890248 61
1793890253 61
1793890258 60
1793890263 60
1793890268 60
1793890273 60
1793890278 60
1793890283 60
```
</details>

---

