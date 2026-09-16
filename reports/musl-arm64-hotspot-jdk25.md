---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-16 07:30:00 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789557826 48
1789557831 48
1789557836 48
1789557841 48
1789557846 48
1789557851 48
1789557856 48
1789557861 48
1789557866 47
1789557871 47
1789557876 47
1789557881 47
1789557886 47
1789557891 47
1789557896 48
1789557901 48
1789557906 48
1789557911 48
1789557916 48
1789557921 48
```
</details>

---

