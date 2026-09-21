---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (4 unique values: 12-34 cores)</summary>

```
1789989460 14
1789989465 14
1789989470 14
1789989475 14
1789989480 14
1789989485 14
1789989490 14
1789989495 14
1789989500 14
1789989505 14
1789989510 14
1789989516 14
1789989521 12
1789989526 12
1789989531 12
1789989536 12
1789989541 12
1789989546 12
1789989551 32
1789989556 32
```
</details>

---

