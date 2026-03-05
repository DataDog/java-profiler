---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1772735014 28
1772735019 28
1772735024 28
1772735029 32
1772735034 32
1772735039 32
1772735044 32
1772735049 32
1772735054 32
1772735059 32
1772735064 32
1772735069 32
1772735074 32
1772735079 32
1772735084 32
1772735089 32
1772735094 32
1772735099 32
1772735104 32
1772735109 32
```
</details>

---

