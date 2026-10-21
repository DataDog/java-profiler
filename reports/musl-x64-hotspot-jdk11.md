---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 10:48:12 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 82-92 cores)</summary>

```
1792593773 92
1792593778 92
1792593783 92
1792593788 82
1792593793 82
1792593798 82
1792593803 82
1792593808 82
1792593813 82
1792593818 82
1792593823 82
1792593828 84
1792593833 84
1792593838 86
1792593843 86
1792593848 86
1792593853 86
1792593858 86
1792593863 86
1792593868 86
```
</details>

---

