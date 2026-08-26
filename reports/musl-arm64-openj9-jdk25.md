---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 09:45:34 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787751616 43
1787751621 43
1787751626 43
1787751631 43
1787751636 43
1787751641 43
1787751646 43
1787751651 43
1787751656 43
1787751661 43
1787751666 43
1787751671 43
1787751676 48
1787751681 48
1787751686 48
1787751691 48
1787751696 43
1787751701 43
1787751706 43
1787751711 43
```
</details>

---

