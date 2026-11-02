---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:04:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 23 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (4 unique values: 43-47 cores)</summary>

```
1793635088 43
1793635093 45
1793635098 45
1793635103 45
1793635108 45
1793635113 45
1793635118 45
1793635123 45
1793635128 47
1793635133 47
1793635138 45
1793635143 45
1793635148 45
1793635153 45
1793635158 45
1793635163 45
1793635168 45
1793635173 45
1793635178 45
1793635183 45
```
</details>

---

