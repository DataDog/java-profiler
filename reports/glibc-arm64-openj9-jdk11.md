---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 9 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (3 unique values: 20-42 cores)</summary>

```
1789716460 20
1789716465 20
1789716470 20
1789716475 20
1789716480 20
1789716485 20
1789716490 20
1789716495 20
1789716500 20
1789716505 20
1789716510 20
1789716515 20
1789716520 20
1789716525 20
1789716530 20
1789716535 20
1789716540 20
1789716545 42
1789716550 42
1789716555 24
```
</details>

---

