---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 16:41:00 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1792787762 44
1792787767 44
1792787772 44
1792787777 44
1792787782 44
1792787788 44
1792787793 44
1792787798 44
1792787803 44
1792787808 44
1792787813 44
1792787818 44
1792787823 44
1792787828 44
1792787833 39
1792787838 39
1792787843 39
1792787848 39
1792787853 39
1792787858 39
```
</details>

---

