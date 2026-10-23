---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 08:53:55 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 9 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1792759707 25
1792759712 25
1792759717 27
1792759722 27
1792759727 27
1792759732 27
1792759737 27
1792759742 27
1792759747 27
1792759752 27
1792759757 27
1792759762 27
1792759767 27
1792759772 27
1792759777 27
1792759782 27
1792759787 27
1792759792 27
1792759797 27
1792759802 27
```
</details>

---

