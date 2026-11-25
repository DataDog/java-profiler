---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-60 cores)</summary>

```
1795626813 43
1795626818 43
1795626823 43
1795626828 43
1795626833 43
1795626838 43
1795626843 43
1795626848 43
1795626853 43
1795626858 43
1795626863 43
1795626868 43
1795626873 43
1795626878 43
1795626883 43
1795626888 60
1795626893 60
1795626898 60
1795626903 60
1795626908 60
```
</details>

---

