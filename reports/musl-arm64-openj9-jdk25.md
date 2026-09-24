---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 20:34:28 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790209777 46
1790209782 46
1790209787 46
1790209792 46
1790209797 46
1790209802 46
1790209807 46
1790209812 46
1790209817 46
1790209822 46
1790209827 48
1790209832 48
1790209837 48
1790209842 48
1790209847 48
1790209852 48
1790209857 48
1790209862 48
1790209867 48
1790209872 48
```
</details>

---

