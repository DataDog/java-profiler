---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:28:36 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1795706597 40
1795706602 40
1795706607 40
1795706612 40
1795706617 40
1795706622 40
1795706627 40
1795706632 40
1795706637 40
1795706642 40
1795706647 40
1795706652 40
1795706657 40
1795706662 40
1795706667 40
1795706672 40
1795706677 40
1795706682 40
1795706687 40
1795706692 40
```
</details>

---

