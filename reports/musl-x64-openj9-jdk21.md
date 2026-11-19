---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:47:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 41-43 cores)</summary>

```
1795113777 42
1795113782 42
1795113787 42
1795113792 43
1795113797 43
1795113802 43
1795113807 43
1795113812 43
1795113817 43
1795113822 43
1795113827 43
1795113832 43
1795113837 43
1795113842 43
1795113847 43
1795113852 43
1795113857 43
1795113862 43
1795113867 43
1795113872 43
```
</details>

---

