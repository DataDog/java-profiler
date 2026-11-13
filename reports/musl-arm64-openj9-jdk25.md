---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:03:39 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794567552 48
1794567557 48
1794567562 48
1794567567 48
1794567572 48
1794567577 48
1794567582 48
1794567587 48
1794567592 48
1794567597 48
1794567602 48
1794567607 48
1794567612 48
1794567617 48
1794567622 48
1794567627 48
1794567632 48
1794567637 48
1794567642 48
1794567647 48
```
</details>

---

