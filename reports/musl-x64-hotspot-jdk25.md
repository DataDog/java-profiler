---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-12 07:47:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 12 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1770900142 32
1770900147 32
1770900152 32
1770900157 32
1770900162 32
1770900167 32
1770900172 32
1770900177 32
1770900182 32
1770900187 32
1770900192 32
1770900197 32
1770900202 32
1770900207 32
1770900212 32
1770900217 32
1770900222 32
1770900227 32
1770900232 32
1770900237 32
```
</details>

---

