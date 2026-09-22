---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:10:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 42-65 cores)</summary>

```
1790096717 42
1790096722 42
1790096727 42
1790096732 42
1790096737 42
1790096742 43
1790096747 43
1790096752 43
1790096757 43
1790096762 43
1790096767 43
1790096773 43
1790096778 43
1790096783 43
1790096788 43
1790096793 43
1790096798 43
1790096803 43
1790096808 43
1790096813 65
```
</details>

---

