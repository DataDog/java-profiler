---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 07:33:16 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 13 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1787311647 46
1787311652 46
1787311657 46
1787311662 46
1787311667 46
1787311672 46
1787311677 48
1787311682 48
1787311687 48
1787311692 48
1787311697 48
1787311702 48
1787311707 48
1787311712 48
1787311717 48
1787311722 48
1787311727 48
1787311732 48
1787311737 48
1787311742 48
```
</details>

---

