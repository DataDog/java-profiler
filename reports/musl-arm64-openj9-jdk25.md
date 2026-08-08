---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-08 00:57:01 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1786164823 41
1786164828 41
1786164833 41
1786164838 43
1786164843 43
1786164848 43
1786164853 43
1786164858 43
1786164863 43
1786164868 43
1786164873 43
1786164878 43
1786164883 43
1786164888 43
1786164894 43
1786164899 43
1786164904 43
1786164909 43
1786164914 43
1786164919 43
```
</details>

---

