---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 50 |

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
1789716734 28
1789716739 28
1789716744 28
1789716749 28
1789716754 28
1789716759 28
1789716764 28
1789716769 28
1789716774 28
1789716779 28
1789716784 28
1789716789 28
1789716794 28
```
</details>

---

