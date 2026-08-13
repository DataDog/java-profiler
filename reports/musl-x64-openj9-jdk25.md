---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 04:00:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 42-58 cores)</summary>

```
1786607769 58
1786607774 58
1786607779 42
1786607784 42
1786607789 42
1786607794 42
1786607799 47
1786607804 47
1786607809 45
1786607814 45
1786607819 45
1786607824 45
1786607829 45
1786607834 49
1786607839 49
1786607844 49
1786607849 49
1786607854 49
1786607859 49
1786607864 49
```
</details>

---

