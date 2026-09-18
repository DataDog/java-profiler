---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

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
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1789716699 48
1789716704 48
1789716709 48
1789716714 28
1789716719 28
1789716724 28
1789716729 28
1789716735 28
1789716740 28
1789716745 28
1789716750 28
1789716755 28
1789716760 28
1789716765 28
1789716770 28
1789716775 28
1789716780 28
1789716785 28
1789716790 28
1789716795 28
```
</details>

---

