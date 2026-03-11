---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 04:33:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 12 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1041 |
| Sample Rate | 17.35/sec |
| Health Score | 1084% |
| Threads | 13 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 61-62 cores)</summary>

```
1773217679 62
1773217684 62
1773217689 62
1773217694 61
1773217699 61
1773217704 61
1773217709 62
1773217714 62
1773217719 61
1773217724 61
1773217729 61
1773217734 61
1773217739 61
1773217744 61
1773217749 61
1773217754 61
1773217759 61
1773217764 61
1773217769 61
1773217774 61
```
</details>

---

