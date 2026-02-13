---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-13 07:52:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 12 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 42-49 cores)</summary>

```
1770986853 49
1770986858 49
1770986863 49
1770986868 49
1770986873 49
1770986878 44
1770986883 44
1770986888 44
1770986893 44
1770986898 44
1770986903 44
1770986908 44
1770986913 44
1770986918 44
1770986923 44
1770986928 44
1770986933 44
1770986938 44
1770986943 44
1770986948 44
```
</details>

---

