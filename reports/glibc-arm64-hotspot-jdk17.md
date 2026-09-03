---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-03 14:43:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 10 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 13 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1788460717 45
1788460722 48
1788460727 48
1788460732 48
1788460737 48
1788460742 48
1788460747 48
1788460752 48
1788460757 48
1788460762 48
1788460767 48
1788460772 48
1788460777 48
1788460782 48
1788460787 48
1788460792 48
1788460797 48
1788460802 43
1788460807 43
1788460812 43
```
</details>

---

