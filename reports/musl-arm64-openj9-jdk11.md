---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 07:16:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (5 unique values: 23-30 cores)</summary>

```
1786446591 23
1786446596 26
1786446601 26
1786446606 27
1786446611 27
1786446616 25
1786446621 25
1786446626 25
1786446631 25
1786446636 25
1786446641 25
1786446646 25
1786446651 25
1786446656 25
1786446661 25
1786446666 25
1786446671 25
1786446676 25
1786446681 30
1786446686 30
```
</details>

---

