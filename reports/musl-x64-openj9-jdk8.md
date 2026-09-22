---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:14:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-63 cores)</summary>

```
1790097005 53
1790097010 53
1790097015 53
1790097020 53
1790097025 53
1790097030 53
1790097035 63
1790097040 63
1790097045 63
1790097050 63
1790097055 63
1790097060 63
1790097065 63
1790097070 63
1790097075 63
1790097080 63
1790097085 63
1790097090 63
1790097095 63
1790097100 63
```
</details>

---

