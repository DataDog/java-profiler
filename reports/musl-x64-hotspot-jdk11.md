---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:29:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 8 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1792977829 94
1792977834 94
1792977839 94
1792977844 96
1792977849 96
1792977854 92
1792977859 92
1792977864 92
1792977869 92
1792977874 92
1792977879 92
1792977884 92
1792977889 92
1792977894 92
1792977899 92
1792977904 92
1792977909 92
1792977914 92
1792977919 92
1792977924 92
```
</details>

---

