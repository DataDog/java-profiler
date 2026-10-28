---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:27:44 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793204587 48
1793204592 48
1793204597 48
1793204602 48
1793204607 48
1793204612 48
1793204617 48
1793204622 48
1793204627 48
1793204632 48
1793204637 48
1793204642 48
1793204647 48
1793204652 48
1793204657 48
1793204662 48
1793204667 48
1793204672 48
1793204677 48
1793204682 48
```
</details>

---

