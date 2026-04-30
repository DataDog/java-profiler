---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 19:50:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777592829 64
1777592834 64
1777592839 64
1777592844 64
1777592849 64
1777592854 64
1777592859 64
1777592864 64
1777592869 64
1777592874 64
1777592879 64
1777592884 64
1777592889 64
1777592894 64
1777592899 64
1777592904 64
1777592909 64
1777592914 64
1777592919 64
1777592924 64
```
</details>

---

