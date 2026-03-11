---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 13 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1773252122 54
1773252127 54
1773252132 54
1773252137 54
1773252142 54
1773252147 54
1773252152 54
1773252157 54
1773252162 54
1773252167 54
1773252172 54
1773252177 54
1773252182 54
1773252187 54
1773252192 54
1773252197 49
1773252202 49
1773252207 49
1773252212 49
1773252217 49
```
</details>

---

