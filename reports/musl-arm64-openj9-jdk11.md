---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 14:20:07 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787422612 43
1787422617 43
1787422622 48
1787422627 48
1787422632 48
1787422637 48
1787422642 48
1787422647 48
1787422652 48
1787422657 48
1787422662 48
1787422667 48
1787422672 48
1787422677 48
1787422682 48
1787422687 48
1787422692 48
1787422697 48
1787422702 48
1787422707 48
```
</details>

---

