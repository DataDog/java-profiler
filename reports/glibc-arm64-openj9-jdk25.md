---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:41:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789673471 48
1789673476 48
1789673481 48
1789673486 48
1789673491 48
1789673496 48
1789673501 48
1789673506 48
1789673511 48
1789673516 47
1789673521 47
1789673526 47
1789673531 47
1789673536 47
1789673541 47
1789673546 47
1789673551 47
1789673556 47
1789673561 47
1789673566 48
```
</details>

---

