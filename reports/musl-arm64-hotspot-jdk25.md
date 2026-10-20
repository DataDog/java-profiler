---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 17:52:27 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (1 unique values: 45-45 cores)</summary>

```
1792532753 45
1792532758 45
1792532763 45
1792532768 45
1792532773 45
1792532778 45
1792532783 45
1792532789 45
1792532794 45
1792532799 45
1792532804 45
1792532809 45
1792532814 45
1792532819 45
1792532824 45
1792532829 45
1792532834 45
1792532839 45
1792532844 45
1792532849 45
```
</details>

---

