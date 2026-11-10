---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1794323788 71
1794323793 71
1794323798 71
1794323803 71
1794323808 71
1794323813 71
1794323818 71
1794323823 79
1794323828 79
1794323833 79
1794323838 79
1794323843 79
1794323848 79
1794323853 79
1794323858 79
1794323863 79
1794323868 79
1794323873 79
1794323878 79
1794323883 79
```
</details>

---

