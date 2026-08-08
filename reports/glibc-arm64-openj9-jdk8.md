---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-08 00:56:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1786164773 54
1786164778 54
1786164783 54
1786164788 54
1786164793 54
1786164798 54
1786164803 54
1786164808 54
1786164813 54
1786164818 54
1786164823 54
1786164828 54
1786164833 54
1786164838 59
1786164843 59
1786164848 59
1786164853 59
1786164858 59
1786164863 59
1786164868 59
```
</details>

---

