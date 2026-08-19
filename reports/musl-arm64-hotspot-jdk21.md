---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 04:26:40 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787127669 46
1787127674 46
1787127679 46
1787127684 46
1787127689 46
1787127694 46
1787127699 46
1787127704 48
1787127709 48
1787127714 43
1787127719 43
1787127724 43
1787127730 43
1787127735 43
1787127740 43
1787127745 43
1787127750 43
1787127755 43
1787127760 43
1787127765 43
```
</details>

---

