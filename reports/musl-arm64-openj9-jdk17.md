---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:35:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 12 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794997787 34
1794997792 34
1794997797 34
1794997802 34
1794997807 34
1794997812 34
1794997817 34
1794997822 34
1794997827 34
1794997832 34
1794997837 34
1794997842 34
1794997847 34
1794997852 34
1794997857 34
1794997862 29
1794997867 29
1794997872 29
1794997877 29
1794997883 29
```
</details>

---

