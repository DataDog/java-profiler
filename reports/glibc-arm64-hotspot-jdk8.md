---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-27 11:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 40 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1795796737 35
1795796742 35
1795796747 35
1795796752 35
1795796757 35
1795796762 30
1795796767 30
1795796772 30
1795796777 30
1795796782 30
1795796787 30
1795796792 30
1795796797 30
1795796802 30
1795796807 30
1795796812 30
1795796817 30
1795796822 30
1795796827 30
1795796832 30
```
</details>

---

