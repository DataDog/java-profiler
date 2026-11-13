---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:24:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 463 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 8 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 61-71 cores)</summary>

```
1794604717 69
1794604722 69
1794604727 69
1794604732 69
1794604737 69
1794604742 69
1794604747 69
1794604752 69
1794604757 69
1794604762 69
1794604767 69
1794604772 69
1794604777 69
1794604782 69
1794604787 69
1794604792 69
1794604797 69
1794604802 69
1794604807 69
1794604812 71
```
</details>

---

