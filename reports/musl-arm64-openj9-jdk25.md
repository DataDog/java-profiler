---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 01:06:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 11 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1792472552 34
1792472557 34
1792472562 34
1792472567 34
1792472572 34
1792472577 34
1792472582 34
1792472587 34
1792472592 34
1792472597 34
1792472602 34
1792472607 29
1792472612 29
1792472617 29
1792472622 29
1792472627 29
1792472632 29
1792472637 29
1792472642 29
1792472647 29
```
</details>

---

