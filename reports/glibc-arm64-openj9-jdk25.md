---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-08 00:56:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 24 |
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
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 14-24 cores)</summary>

```
1786164772 14
1786164777 14
1786164782 14
1786164788 14
1786164793 14
1786164798 14
1786164803 14
1786164808 14
1786164813 14
1786164818 14
1786164823 19
1786164828 19
1786164833 19
1786164838 19
1786164843 19
1786164848 19
1786164853 19
1786164858 19
1786164863 19
1786164868 19
```
</details>

---

