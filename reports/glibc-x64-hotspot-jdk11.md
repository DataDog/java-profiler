---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:29:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 67-96 cores)</summary>

```
1792977839 94
1792977844 94
1792977849 94
1792977854 94
1792977859 94
1792977864 94
1792977869 96
1792977874 96
1792977879 96
1792977884 76
1792977889 76
1792977894 76
1792977899 76
1792977904 76
1792977909 76
1792977914 76
1792977919 76
1792977924 76
1792977929 76
1792977934 76
```
</details>

---

