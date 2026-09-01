---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 12:28:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1788279653 46
1788279658 46
1788279663 46
1788279668 46
1788279673 46
1788279678 46
1788279683 46
1788279688 46
1788279693 46
1788279698 46
1788279703 46
1788279708 48
1788279713 48
1788279718 48
1788279723 48
1788279728 48
1788279733 48
1788279738 48
1788279743 48
1788279748 48
```
</details>

---

