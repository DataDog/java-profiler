---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 04:26:40 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787127689 46
1787127694 46
1787127699 46
1787127704 48
1787127709 48
1787127714 43
1787127719 43
1787127724 43
1787127729 43
1787127734 43
1787127739 43
1787127744 43
1787127749 43
1787127754 43
1787127759 43
1787127764 43
1787127769 43
1787127774 43
1787127779 43
1787127784 43
```
</details>

---

